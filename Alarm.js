let alarmTime = null;
let alarmActive = false;

function current_time() {
    const now = new Date();
    const hour = String(now.getHours()).padStart(2, "0");
    const minutes = String(now.getMinutes()).padStart(2, "0");
    const seconds = String(now.getSeconds()).padStart(2, "0");
    document.getElementById("current-time").textContent = `${hour}:${minutes}:${seconds}`;
};

function setAlarm() {
    const input = document.getElementById('alarm-time').value;
    if (!input) {
        alert("Please set a valid alarm time.");
        return;
    };
    alarmTime = input;
    alarmActive = false;
    alert(`Alarm set for ${alarmTime}`);
};

function checkAlarm() {
    if (alarmTime && !alarmActive) {
        const now = new Date();
        const currentFormattedTime = `${String(now.getHours()).padStart(2, "0")}:${String(now.getMinutes()).padStart(2, "0")}`;

        if (currentFormattedTime === alarmTime) {
            alarmActive = true;
            document.getElementById("current-time").classList.add("alarm-active");
            alert("Time's up! Alarm triggered.");
            alarmTime = null; 
        };
    };
};

function stopAlarm() {
    alarmActive = false;
    alarmTime = null;
    const currentDisplay = document.getElementById("current-time");
    currentDisplay.classList.remove("alarm-active");
    alert("Alarm stopped.");
};

document.getElementById("set-alarm").addEventListener("click", setAlarm);
document.getElementById("stop-alarm").addEventListener("click", stopAlarm);

setInterval(() => {
    current_time();
    checkAlarm();
}, 1000);
