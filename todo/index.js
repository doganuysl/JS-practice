// references for form and list elements
const taskForm = document.getElementById("task-form");
const taskList = document.getElementById("task-list");
const taskInput = document.getElementById("task-input");

// prevent send form
taskForm.addEventListener("submit", function (event) {
  event.preventDefault();

  // take input value
  const task = taskInput.value;

  // if not null
  if (task && !task.includes(" ")) {
    // set the task to local storage

    // add <li>
    const liDOM = document.createElement("li");

    const taskKey = `task-${Date.now()}`;
    localStorage.setItem(taskKey, task);

    // add input to in <li>
    liDOM.innerHTML = localStorage.getItem(taskKey);

    //add <li> to the list
    taskList.appendChild(liDOM);

    // add delete button
    const deleteButton = document.createElement("button");
    deleteButton.innerHTML = "Delete";

    // Delete <li> when click "delete" button
    deleteButton.addEventListener("click", function (event) {
      liDOM.parentNode.removeChild(liDOM);
      // also remove the task from local storage
      localStorage.removeItem(taskKey);
    });

    liDOM.appendChild(deleteButton);

    // <li> elemanına tıklandığında üstünü çizme ve renk değiştirme işlemleri
    liDOM.addEventListener("click", function (event) {
      this.classList.toggle("completed"); //sadece add yaparsan ilk tıklamada oluyor kaldırmak istersen tekrar tıklayına çalışmıyor dolayısıyla toggle öncekini kaldırıp yerine belirlediğini koyuyor
    });

    // clear input
    taskInput.value = "";
  } else if (task.includes(" ")) {
    //if empty/space
    alert("Lütfen bir görev giriniz!");

    taskInput.value = "";
  } else alert("Lütfen bir görev giriniz!");
});

// when the page loads
window.addEventListener("load", function () {
  // get all tasks from local storage
  for (let i = 0; i < localStorage.length; i++) {
    const key = localStorage.key(i);
    const value = localStorage.getItem(key);

    // add <li>
    const liDOM = document.createElement("li");

    // add task value to in <li>
    liDOM.innerHTML = value;

    let deleteButton = document.createElement("button");
    deleteButton.innerHTML = "Delete";
    deleteButton.id = key;

    deleteButton.addEventListener("click", function (event) {
      let element = this.id;
      liDOM.parentNode.removeChild(liDOM);

      // also remove the task from local storage
      localStorage.removeItem(element);
    });
    liDOM.appendChild(deleteButton);

    liDOM.addEventListener("click", function (event) {
      this.classList.toggle("completed"); //sadece add yaparsan ilk tıklamada oluyor kaldırmak istersen tekrar tıklayına çalışmıyor dolayısıyla toggle öncekini kaldırıp yerine belirlediğini koyuyor
    });

    // add <li> to the list
    taskList.appendChild(liDOM);
  }
});
