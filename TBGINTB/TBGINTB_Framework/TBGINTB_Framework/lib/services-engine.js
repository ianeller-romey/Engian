
var ServicesEngine = function () {
    this.messengerEngine = globalMessengerEngine;

    this.messengerEngine.register("UserInputManager.loadNounsForParagraphState", this, this.loadNounsForParagraphState);
};

ServicesEngine.prototype.loadAllVerbTypes = function () {
    var that = this;

    $.ajax({
        url: "http://ironandrose/gintub/lion/gintubservices/GinTubService.svc/LoadAllVerbTypes",
        type: 'get',
        dataType: 'text',
        contentType: 'application/json',
        success: function (data, status) {
            var allData = JSON.parse(data);
            that.messengerEngine.post("ServicesEngine.loadAllVerbTypes", allData.LoadAllVerbTypesResult);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};

ServicesEngine.prototype.loadNounsForParagraphState = function (paragraphStateId) {
    var that = this;

    $.ajax({
        url: "http://ironandrose/gintub/lion/gintubservices/GinTubService.svc/LoadNounsForParagraphState",
        type: 'post',
        dataType: 'text',
        contentType: 'application/json',
        data: JSON.stringify({
            paragraphStateId: paragraphStateId
        }),
        success: function (data, status) {
            var allData = JSON.parse(data);
            that.messengerEngine.post("ServicesEngine.loadNounsForParagraphState", allData.LoadNounsForParagraphStateResult);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};

ServicesEngine.prototype.loadGame = function (playerIdGuid) {
    var that = this;

    $.ajax({
        url: "http://ironandrose/gintub/lion/gintubservices/GinTubService.svc/LoadGame",
        type: 'post',
        dataType: 'text',
        contentType: 'application/json',
        data: JSON.stringify({
            playerId: playerIdGuid
        }),
        success: function (data, status) {
            var allData = JSON.parse(data);
            that.messengerEngine.post("ServicesEngine.loadGame", allData.LoadGameResult);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};

ServicesEngine.prototype.loadRoomXYZ = function (playerIdGuid, areaInt, xInt, yInt, zInt, currentTimeDateTime) {
    var that = this;

    $.ajax({
        url: "http://ironandrose/gintub/lion/gintubservices/GinTubService.svc/LoadRoom",
        type: 'post',
        dataType: 'text',
        contentType: 'application/json',
        data: JSON.stringify({
            playerId: playerIdGuid,
            area: areaInt,
            x: xInt,
            y: yInt,
            z: zInt
        }),
        success: function (data, status) {
            that.messengerEngine.post("ServicesEngine.loadRoomXYZ", roomData);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};