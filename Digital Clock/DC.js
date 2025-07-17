function time() {
    const now = new Date;
    let hour = now.getHours();
    let min = now.getMinutes();
    let sec = now.getSeconds();
    let period = hour >= 12 ? "AM" : "PM";
    hour = hour % 12 || 12

    hour = hour < 10 ? "0" + hour : hour;
    min = min < 10 ? "0" + min : min;
    sec = sec < 10 ? "0" + sec : sec;


    const timesetter = `${hour}:${min}:${sec} ${period}`;
    document.getElementById('Digital').textContent = timesetter

}


time();
setInterval(time, 1000);