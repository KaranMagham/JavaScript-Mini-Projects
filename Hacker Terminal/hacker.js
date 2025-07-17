const arr = [
    "Initializing Hacking...",
    "Analyzing files...",
    "Searching for files...",
    "Target found...",
    "Accessing data...",
    "Sending data to server...",
    "Changing data...",
    "Cleaning up..."
];

const randomDelay = (min = 1000, max = 4000) => {
    return new Promise(resolve => {
        const delay = Math.random() * (max - min) + min;
        setTimeout(resolve, delay);
        console.log(delay)
    });
};

const terminal = async (text) => {
    const main = document.getElementById('main');
    main.innerHTML += `<span>${text}</span><br><br>`;
    window.scrollTo(0, document.body.scrollHeight);
    await randomDelay();
};

async function startHacking() {
    for (const item of arr) {
        await terminal(item);
    }
    document.getElementById('main').innerHTML += `<span style="color: red;">✔️ Hacking Complete!</span>`;
}

startHacking();
