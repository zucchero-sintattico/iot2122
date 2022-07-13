const source = new EventSource("/sse");
source.onmessage = function(event) {
    var data = JSON.parse(event.data);
    console.log(data);
};

// get request to /dashboard-status
const dashboardStatus = new XMLHttpRequest();
dashboardStatus.open("GET", "/dashboard-status");
dashboardStatus.onload = function() {
    var data = JSON.parse(dashboardStatus.responseText);
    console.log(data);
}
dashboardStatus.send();
