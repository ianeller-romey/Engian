
var InterfaceManager = function (locationId, paragraphsId) {
    this.location = $(locationId);
    this.paragraphs = $(paragraphsId);
    this.messenger = globalMessengerEngine;

    this.messenger.register("ServicesEngine.loadRoom", this, this.loadRoom);
};

InterfaceManager.prototype.loadRoom = function (roomData) {
    var aaa = 0;
};