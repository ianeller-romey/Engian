
var InterfaceManager = function (locationId, paragraphsId, userInterfaceManager) {
    this.location = $(locationId);
    this.paragraphs = $(paragraphsId);
    this.userInput = userInterfaceManager;
    this.messenger = globalMessengerEngine;

    this.messenger.register("ServicesEngine.loadGame", this, this.loadGame);
    this.messenger.register("ServicesEngine.loadRoom", this, this.loadRoom);
};

InterfaceManager.prototype.loadGame = function (areaAndRoomData) {
    this.loadRoom(areaAndRoomData.RoomStates);
};

InterfaceManager.prototype.loadRoom = function (roomData) {
    var roomState = roomData[0];

    this.location.attr('src', roomState.Location);

    var paragraphStates = roomState.ParagraphStates;
    for (var i = 0, len = paragraphStates.length; i < len; i++) {
        var that = this;
        this.paragraphs.append($('<span/>', {
            class: 'unParagraph',
            text: paragraphStates[i].Text
        }).click(function (e) {
            that.userInput.closeAndReopenVerbList(e.pageX, e.pageY);
        }));
        this.paragraphs.append(' ');
    }
};