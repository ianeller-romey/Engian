
var ServicesEngine = function () {
    this.messenger = globalMessengerEngine;
};

ServicesEngine.prototype.loadRoom = function (playerIdGuid, areaInt, xInt, yInt, zInt, currentTimeDateTime) {
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
            that.messenger.post("ServicesEngine.loadRoom", roomData);
        },
        error: function (request, status, error) {
            var iii = 0;
        }
    });
};