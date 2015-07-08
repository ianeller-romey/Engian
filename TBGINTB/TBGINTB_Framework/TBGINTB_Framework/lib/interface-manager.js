
var InterfaceManager = function (locationId, paragraphsId) {
    this.locationElem = $(locationId);
    this.paragraphsElem = $(paragraphsId);

    this.messengerEngine = globalMessengerEngine;

    this.paragraphs = null;
    this.nouns = null;

    this.messengerEngine.register("ServicesEngine.loadGame", this, this.loadGame);
    this.messengerEngine.register("ServicesEngine.loadRoom", this, this.loadRoom);
};

InterfaceManager.prototype.loadGame = function (areaAndRoomData) {
    this.loadRoom(areaAndRoomData.RoomStates);
};

InterfaceManager.prototype.loadRoom = function (roomData) {
    var that = this;
    this.paragraphs = {};
    this.nouns = {};

    var roomState = roomData[0];

    this.locationElem.attr("src", roomState.Location);

    var createParagraphSpanClick = function (psId) {
        return function (e) {
            that.messengerEngine.post("InterfaceManager.unParagraphClick", e.pageX, e.pageY, psId);
        };
    };
    var createWordSpanClick = function (wId) {
        return function (e) {
            that.messengerEngine.post("InterfaceManager.unWordClick", e.pageX, e.pageY, wId);
        };
    };

    var paragraphStates = roomState.ParagraphStates;
    var i = 0;
    var len = paragraphStates.length;
    for (; i < len; ++i) {
        var ps = paragraphStates[i];
        if (ps.Words.length == 0) {
            continue;
        }

        var paragraphSpan = $("<span/>", {
            class: "unParagraph"
        }).click(createParagraphSpanClick(ps.Id)).mouseenter(function (e) {
            $(this).addClass("unHover");
        }).mouseleave(function (e) {
            $(this).removeClass("unHover");
        });

        this.paragraphs[paragraphSpan] = { id: ps.Id, order: ps.Order };

        var words = paragraphStates[i].Words;
        var j = 0;
        var len2 = words.length;
        for(; j < len2; ++j) {
            var w = words[j];
            paragraphSpan.append($("<span/>", { 
                class: "unWord",
                text: w.Text
            }).click(createWordSpanClick(w.Id)).mouseenter(function (e) {
                $(this).addClass("unHover").parent().removeClass("unHover");
            }).mouseleave(function (e) {
                $(this).removeClass("unHover").parent().addClass("unHover");
            }));

            if (w.NounId != null) {
                this.nouns[w] = { id: w.NounId };
            }

            if (j != len2 - 1) {
                w = words[j + 1];
                wt = w.Text;
                if (wt != "." &&
                    wt != "," &&
                    wt != ";" &&
                    wt != ":" &&
                    wt != "?" &&
                    wt != "!" &&
                    wt != "\"") {
                    paragraphSpan.append(" ");
                }
            }
        }
        this.paragraphsElem.append(paragraphSpan);
        this.paragraphsElem.append(" ");
    }
};