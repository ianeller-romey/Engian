
var ServicesEngine = function () {
    this.messenger = globalMessengerEngine;
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
            that.messenger.post("ServicesEngine.loadGame", allData.LoadGameResult);
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
            that.messenger.post("ServicesEngine.loadRoomXYZ", roomData);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};