// script.js

const colors = ["#24d05a", "#eb4888", "#10a2f5", "#e9bc3f"];

function getRandomColor() {
    return colors[Math.floor(Math.random() * colors.length)];
}

function setRandomLinkColor() {
    Array.from(document.getElementsByTagName("a")).forEach((e) => {
        e.style.textDecorationColor = getRandomColor();
    });
}

function setColorHoverListener() {
    Array.from(document.querySelectorAll("a, button")).forEach((e) => {
        e.addEventListener("mouseover", setRandomLinkColor);
    });
}

// Run when DOM is fully loaded
document.addEventListener("DOMContentLoaded", () => {
    setRandomLinkColor();
    setColorHoverListener();
});
