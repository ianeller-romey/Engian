
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
    this.verbListElem = $(idOfVerbList);
    this.interfaceElem = this.verbListElem.parent("div");
    this.states = {
        closed: 0,
        updating: 1,
        open: 2
    };
    this.state = this.states.closed;
    this.actionQueue = new ActionQueue(3);
};

VerbList.prototype.openExec = function(clientX, clientY) {
    if(this.state === this.states.open) {
        return;
    }

    var that = this;

    // create all the divs that represent Verbs
    // TODO: Load from DB
    var i = 0;
    for (; i < 3; ++i) {
        var div = $(document.createElement("div"));
        div.addClass("verb");
        div.text("TEST");
        div.click(function () {
            that.close();
        });
        this.verbListElem.append(div);
    }

    // set position immediately
    this.verbListElem.css({
        left: clientX - this.interfaceElem.offset().left,
        top: clientY - this.interfaceElem.offset().top - 20
    });
    // animate opening
    this.verbListElem.animateAuto("width", 50, function () {
        that.verbListElem.animateAuto("height", 50, function () {
            that.verbListElem.animate({
                padding: 10
            }, 50, function () {
                if (that.actionQueue.isEmpty()) {
                    that.state = that.states.open;
                }
                else {
                    that.update();
                }
            });
        });
    });
};

VerbList.prototype.closeExec = function() {
    if(this.state === this.states.closed){
        return;
    }

    var that = this;

    // animate closing in reverse order
    this.verbListElem.animate({
        height: 0
    }, 50, function () {
        that.verbListElem.animate({
            width: 0
        }, 50, function () {
            that.verbListElem.animate({
                padding: 0
            }, 50, function () {
                that.verbListElem.empty();
                if (that.actionQueue.isEmpty()) {
                    that.state = that.states.closed;
                }
                else {
                    that.update();
                }
            });
        });
    });
};

VerbList.prototype.open = function (clientX, clientY) {
    if (this.state === this.states.updating) {
        return;
    }
    this.state = this.states.updating;
    this.actionQueue.push(this, this.openExec, clientX, clientY);
    this.update();
};

VerbList.prototype.close = function () {
    if (this.state === this.states.updating) {
        return;
    }
    this.state = this.states.updating;
    this.actionQueue.push(this, this.closeExec);
    this.update();
};

VerbList.prototype.closeAndReopen = function (clientX, clientY) {
    if (this.state === this.states.updating) {
        return;
    }
    this.state = this.states.updating;
    this.actionQueue.push(this, this.closeExec);
    this.actionQueue.push(this, this.openExec, clientX, clientY);
    this.update();
};

VerbList.prototype.update = function () {
    if(!this.actionQueue.isEmpty()){
        this.actionQueue.pop();
    }
};

VerbList.prototype.continueUpdating = function () {
    this.actionQueue.pop();
};

var UserInputManager = function () {
    this.verbList = new VerbList("#verbList");
};

UserInputManager.prototype.openVerbList = function (clientX, clientY) {
    this.verbList.open(clientX, clientY);
};

UserInputManager.prototype.closeVerbList = function () {
    this.verbList.close();
};

UserInputManager.prototype.closeAndReopenVerbList = function (clientX, clientY) {
    if (this.verbList.state === this.verbList.states.open) {
        this.verbList.closeAndReopen(clientX, clientY);
    }
    else {
        this.verbList.open(clientX, clientY);
    }
};