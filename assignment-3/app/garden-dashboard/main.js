const source = new EventSource("/sse");
source.onmessage = function(event) {
    var data = JSON.parse(event.data);

    for (let key in data) {
        switch (key) {
            case "status":
                updateStatus(data[key]);
                $("#status").text(data[key]);
                break;
            case "led1":
                $("#led1").text(data[key] == 1 ? "ON" : "OFF");
                break;
            case "led2":
                $("#led2").text(data[key] == 1 ? "ON" : "OFF");
                break;
            case "led3":
                $("#led3").text(data[key] * 25 + "%");
                break;
            case "led4":
                $("#led4").text(data[key] * 25 + "%");
                break;
            default:
                $("#" + key).text(data[key]);
        }
    }
};

// get request to /dashboard-status
const dashboardStatus = new XMLHttpRequest();
dashboardStatus.open("GET", "/dashboard-status");
dashboardStatus.onload = function() {
    const data = JSON.parse(dashboardStatus.responseText);

    $("#status").text(data.status);
    updateStatus(data.status);

    $("#light").text(data.light);
    $("#temperature").text(data.temperature);

    $("#led1").text(data.led1 == 1 ? "ON" : "OFF");
    $("#led2").text(data.led2 == 1 ? "ON" : "OFF");
    $("#led3").text(data.led3);
    $("#led4").text(data.led4);

    $("#irrigator_status").text(data.irrigator_status);
    $("#irrigator_speed").text(data.irrigation_speed);
}
dashboardStatus.send();

function updateStatus(status) {
    $("body").removeClass();
    switch (status) {
        case "AUTO":
            $("body").addClass("auto");
            break;
        case "MANUAL":
            $("body").addClass("manual");
            break;
        case "ALARM":
            $("body").addClass("alarm");
            break;
    }
}