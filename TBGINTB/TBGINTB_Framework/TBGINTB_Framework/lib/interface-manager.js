
var InterfaceManager = function (locationId, paragraphsId, userInterfaceManager) {
    this.locationElement = $(locationId);
    this.paragraphsElement = $(paragraphsId);
    this.userInputManager = userInterfaceManager;
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

    this.locationElement.attr('src', roomState.Location);

    var paragraphStates = roomState.ParagraphStates;
    for (var i = 0, len = paragraphStates.length; i < len; ++i) {
        var ps = paragraphStates[i];
        if (ps.Words.length == 0) {
            continue;
        }

        var paragraphSpan = $('<span/>', { class: 'unParagraph' });
        paragraphSpan.click(function (e) {
            that.userInputManager.closeAndReopenVerbList(e.pageX, e.pageY);
        });

        this.paragraphs[paragraphSpan] = { id: ps.Id, order: ps.Order };

        var words = paragraphStates[i].Words;
        for(var j = 0, len2 = words.length; j < len2; ++j) {
            var w = words[j];
            paragraphSpan.append($('<span/>', {
                class: 'unWord',
                text: w.Text
            }).click(function (e) {
                that.userInputManager.closeAndReopenVerbList(e.pageX, e.pageY);
            }));

            if (w.NounId != null) {
                this.nouns[w] = { id: w.NounId };
            }

            if (j != len2 - 1) {
                w = words[j + 1];
                wt = w.Text;
                if (wt != '.' &&
                    wt != ',' &&
                    wt != ';' &&
                    wt != ':' &&
                    wt != '?' &&
                    wt != '!' &&
                    wt != '"') {
                    paragraphSpan.append(' ');
                }
            }
        }
        this.paragraphsElement.append(paragraphSpan);
        this.paragraphsElement.append(' ');
    }
};