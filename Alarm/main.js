let alarmActive = false;
        let alarmTime = null;

        function currentTime() {
            const now = new Date();
            const hour = String(now.getHours()).padStart(2, "0");
            const min = String(now.getMinutes()).padStart(2, "0");
            const sec = String(now.getSeconds()).padStart(2, "0");
            document.getElementById("current-time").textContent = `${hour}:${min}:${sec}`;
        };


        function setAlarm() {
            const input = document.getElementById('alarm-time').value;
            if (!input) {
                alert("Please set a valid alarm time...");
                return;
            };
            alarmActive = false;
            alarmTime = input;
            alert(`Alarm set for ${alarmTime}`);
        };

        function alarmChecking() {
            if (alarmTime && !alarmActive) {
                const now = new Date();
                const currentFormattedTime = `${String(now.getHours()).padStart(2, "0")}:${String(now.getMinutes()).padStart(2, "0")}`;

                if (currentFormattedTime == alarmTime) {
                    alarmActive = true;
                    document.getElementById('current-time').classList.add("alarm-active");
                    alert("Time's up! Alarm triggered.");
                    alarmTime = null;
                };
            };
        };

        function stopAlarm() {
            alarmActive = false;
            alarmTime = null;
            const cDis = document.getElementById('current-time');
            cDis.classList.remove("alarm-active");
            alert("Alarm stoped...");
        };

        document.getElementById('set-alarm').addEventListener('click', setAlarm);
        document.getElementById('stop-alarm').addEventListener('click', stopAlarm);

        setInterval(() => {
            currentTime();
            alarmChecking();
        }, 1000);