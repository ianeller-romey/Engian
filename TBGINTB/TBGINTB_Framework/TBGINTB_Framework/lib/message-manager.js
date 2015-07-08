
var MessageManager = function (messageTopId, messageBottomId, messageTextId, messageChoicesId) {
    this.messageTopElem = $(messageTopId);
    this.messageBottomElem = $(messageBottomId);
    this.messageTextElem = $(messageTextId);
    this.messageChoicesElem = $(messageChoicesId);

    this.messengerEngine = globalMessengerEngine;

    this.messengerEngine.register("ServicesEngine.loadNounsForParagraphState", this, this.loadMessage);
};

MessageManager.prototype.loadMessage = function (messageData) {
    this.messageTopElem.width("100%");
    this.messageBottomElem.width("100%");
};

MessageManager.prototype.unloadMessage = function () {
    this.messageTopElem.width("0px");
    this.messageBottomElem.width("0px");
}