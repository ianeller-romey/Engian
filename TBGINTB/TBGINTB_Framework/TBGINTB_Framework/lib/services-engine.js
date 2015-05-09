
var ServicesEngine = function () {
    this.messenger = globalMessengerEngine;
};

ServicesEngine.prototype.loadRoom = function (playerIdGuid, areaInt, xInt, yInt, zInt, currentTimeDateTime) {
    var that = this;

    $.ajax({
        url: "/gintubservices/GinTubService.svc/RoomDataInitialLoad",
        type: 'post',
        dataType: 'text',
        contentType: 'application/json',
        data: JSON.stringify({
            playerId: playerIdGuid,
            area: areaInt,
            x: xInt,
            y: yInt,
            z: zInt,
            currentTime: currentTimeDateTime
        }),
        success: function (data, status) {
            that.messenger.post("ServicesEngine.loadRoom", roomData);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};