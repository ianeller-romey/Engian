
(jQuery.fn.extend({
    animateAuto: function (prop, speed, callback) {
        var elem;
        var height;
        var width;
        return this.each(function (i, el) {
            el = jQuery(el);
            elem = el.clone().css({ "height": "auto", "width": "auto" }).appendTo("body");
            height = elem.css("height"),
            width = elem.css("width"),
            elem.remove();

            if (prop === "height") {
                el.animate({ "height": height }, speed, callback);
            }
            else if (prop === "width") {
                el.animate({ "width": width }, speed, callback);
            }
            else if (prop === "both") {
                el.animate({ "width": width, "height": height }, speed, callback);
            }
        });
    }
}));

var VerbList = function(idOfVerbList){
    var verbListElem = $(idOfVerbList);
    var verbListElemX = $(idOfVerbList + "X");
    var interfaceElem = verbListElem.parent("div");

    var messengerEngine = globalMessengerEngine;

    this.states = {
        closed: 0,
        updating: 1,
        open: 2
    };
    this.state = this.states.closed;
    var actionQueue = new ActionQueue(3);
    var verbTypesForParagraphs = [{
        name: "Inspect",
        id: -1,
        call: function () {
            messengerEngine.post("VerbList.paragraphClick");
        }
    }];
    var verbTypesForWords = null;
    var activeVerbTypes = null;

    var that = this;

    verbListElemX.click(function () {
        that.close();
    });

    var setActiveVerbTypesForParagraphs = function () {
        activeVerbTypes = verbTypesForParagraphs;
    };

    var setActiveVerbTypesForWords = function () {
        activeVerbTypes = verbTypesForWords;
    };

    var update = function () {
        if (!actionQueue.isEmpty()) {
            actionQueue.pop();
        }
    };

    var continueUpdating = function () {
        actionQueue.pop();
    };

    var openExec = function (clientX, clientY) {
        if (that.state === that.states.open) {
            return;
        }

        // create all the divs that represent Verbs
        var createVerbClick = function (verb) {
            return function (e) {
                verb.call(verb.id);
            };
        };

        var i = 0;
        var len = activeVerbTypes.length;
        for (; i < len; ++i) {
            verbListElem.append($("<div/>", {
                class: "verb",
                text: activeVerbTypes[i].name
            }).click(createVerbClick(activeVerbTypes[i])));
        }

        // set position immediately
        verbListElem.css({
            left: clientX - interfaceElem.offset().left,
            top: clientY - interfaceElem.offset().top - 20
        });
        verbListElem.addClass("verbListShadowed");
        // animate opening
        verbListElem.animateAuto("width", 50, function () {
            verbListElem.animateAuto("height", 50, function () {
                verbListElem.animate({
                    padding: 10
                }, 50, function () {
                    verbListElemX.css({
                        display: "inline"
                    });
                    verbListElemX.animate({
                        opacity: 1
                    }, 25, function () {
                        if (actionQueue.isEmpty()) {
                            that.state = that.states.open;
                        }
                        else {
                            update();
                        }
                    });
                });
            });
        });
    };

    var closeExec = function () {
        if (that.state === that.states.closed) {
            return;
        }

        // animate closing in reverse order
        verbListElemX.animate({
            opacity: 0
        }, 25, function () {
            verbListElemX.css({
                display: "none"
            });
            verbListElem.animate({
                height: 0
            }, 50, function () {
                // remove the verbs after animating down the height, and
                // before anything else, since we see weird artifacts if we
                // remove them last
                $(".verb").remove();
                verbListElem.removeClass("verbListShadowed");
                verbListElem.animate({
                    width: 0
                }, 50, function () {
                    verbListElem.animate({
                        padding: 0
                    }, 50, function () {
                        if (actionQueue.isEmpty()) {
                            that.state = that.states.closed;
                        }
                        else {
                            update();
                        }
                    });
                });
            });
        });
    };

    var open = function (clientX, clientY) {
        if (that.state === that.states.updating) {
            return;
        }
        that.state = that.states.updating;
        actionQueue.push(that, openExec, clientX, clientY);
        update();
    };

    this.openForParagraphs = function (clientX, clientY) {
        setActiveVerbTypesForParagraphs();
        open(clientX, clientY);
    };

    this.openForWords = function (clientX, clientY) {
        setActiveVerbTypesForWords();
        open(clientX, clientY);
    };

    this.close = function () {
        if (that.state === that.states.updating) {
            return;
        }
        that.state = that.states.updating;
        actionQueue.push(that, closeExec);
        update();
    };


    var closeAndReopen = function (clientX, clientY) {
        that.state = that.states.updating;
        actionQueue.push(that, closeExec);
        actionQueue.push(that, openExec, clientX, clientY);
        update();
    };

    this.closeAndReopenForParagraphs = function (clientX, clientY) {
        if (that.state === that.states.updating) {
            return;
        }
        setActiveVerbTypesForParagraphs();
        closeAndReopen(clientX, clientY);
    };

    this.closeAndReopenForWords = function (clientX, clientY) {
        if (that.state === that.states.updating) {
            return;
        }
        setActiveVerbTypesForWords();
        closeAndReopen(clientX, clientY);
    };

    loadAllVerbTypes = function (verbUseData) {
        verbTypesForWords = [];

        var vt = verbUseData.VerbTypes;
        var i = 0;
        var len = vt.length;
        for (; i < len; ++i) {
            var verbType = vt[i];
            verbTypesForWords[i] = {
                id: verbType.Id,
                name: verbType.Name,
                call: function (vId) {
                    messengerEngine.post("VerbList.wordClick", vId);
                }
            };
        }

        messengerEngine.unregister("ServicesEngine.loadAllVerbTypes");
    };

    messengerEngine.register("ServicesEngine.loadAllVerbTypes", that, loadAllVerbTypes);
};

var UserInputManager = function (verbListId) {
    this.verbList = new VerbList(verbListId);

    this.activeId = null;

    this.messengerEngine = globalMessengerEngine;

    this.messengerEngine.register("InterfaceManager.unParagraphClick", this, this.closeAndReopenVerbListForParagraphs);
    this.messengerEngine.register("InterfaceManager.unWordClick", this, this.closeAndReopenVerbListForWords);
    this.messengerEngine.register("VerbList.paragraphClick", this, this.loadNounsForParagraphState)
};

UserInputManager.prototype.openVerbListForParagraphs = function (clientX, clientY) {
    this.verbList.openForParagraphs(clientX, clientY);
};

UserInputManager.prototype.openVerbListForWords = function (clientX, clientY) {
    this.verbList.openForWords(clientX, clientY);
};

UserInputManager.prototype.closeVerbList = function () {
    this.verbList.close();
};

UserInputManager.prototype.closeAndReopenVerbListForParagraphs = function (clientX, clientY, psId) {
    if (this.verbList.state === this.verbList.states.open) {
        this.verbList.closeAndReopenForParagraphs(clientX, clientY);
    }
    else {
        this.verbList.openForParagraphs(clientX, clientY);
    }
    this.activeId = psId;
};

UserInputManager.prototype.closeAndReopenVerbListForWords = function (clientX, clientY, wId) {
    if (this.verbList.state === this.verbList.states.open) {
        this.verbList.closeAndReopenForWords(clientX, clientY);
    }
    else {
        this.verbList.openForWords(clientX, clientY);
    }
    this.activeId = wId;
};

UserInputManager.prototype.loadNounsForParagraphState = function () {
    this.verbList.close();
    this.messengerEngine.post("UserInputManager.loadNounsForParagraphState", this.activeId);
};