let username = prompt("Lütfen adınızı giriniz.");
document.getElementById("myName").innerHTML = username;

let tarih = new Date();

let cDay = tarih.getDate();
let cMonth = tarih.getMonth() + 1;
let cYear = tarih.getFullYear();
// console.log(cDay + "/" + cMonth + "/" + cYear);
document.getElementById("tarih").innerHTML = cDay + "/" + cMonth + "/" + cYear;
/* let currentDate = new Date();
let time =
  currentDate.getHours() +
  ":" +
  currentDate.getMinutes() +
  ":" +
  currentDate.getSeconds();
document.getElementById("saat").innerHTML = time;
console.log(time); */

const element = document.getElementById("currentTime");

setInterval(function () {
  const currentDate = new Date();
  element.innerText =
    currentDate.getHours() +
    ":" +
    currentDate.getMinutes() +
    ":" +
    currentDate.getSeconds();
}, 1000);
