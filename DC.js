function time() {
    const now = new Date;
    let hour = now.getHours();
    let min = now.getMinutes();
    let sec = now.getSeconds();

    hour = hour < 10 ? "0" + hour : hour;
    min = min < 10 ? "0" + min : min;
    sec = sec < 10 ? "0" + sec : sec;

    let period = hour >= 12 ? "PM" : "AM";
    hour = hour % 12 || 12; // Convert to 12-hour format
    const timestr = `${hour}:${min}:${sec} ${period}`;
    document.getElementById("Digital").textContent = timestr;
}

time();
setInterval(time, 1000);


