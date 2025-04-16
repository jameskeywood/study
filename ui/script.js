// Mock data - this will eventually come from C or JSON
const studyData = {
  "01042025": [{ subject: "23412", minutes: 60 }, { subject: "26120", minutes: 180 }, { subject: "26020", minutes: 120 }],
  "03042025": [{ subject: "24112", minutes: 180 }],
};

const maxMinutes = 8 * 60;
const year = 2025;
const month = 3; // 0 based index
// 0th day of next month is the last day of this month
const daysInMonth = new Date(year, month + 1, 0).getDate();
let startDayOffset = new Date(year, month, 1).getDay();
startDayOffset = (startDayOffset + 6) % 7;

function parseCSV(csvText) {
  const lines = csvText.trim().split("\n").slice(1); // skip header
  const result = {};

  lines.forEach(line => {
    const [date, subject, minutes] = line.split(",");
    if (!result[date]) result[date] = [];
    result[date].push({ subject, minutes: parseInt(minutes) });
  });

  return result;
}

function createCalendar() {
  const calendar = document.getElementById("calendar");
  for (let i = 0; i < startDayOffset; i++) {
    calendar.appendChild(document.createElement("div"));
  }

  for (let day = 1; day <= daysInMonth; day++) {
    const dateKey = `${String(day).padStart(2, '0')}042025`;
    const box = document.createElement("div");
    box.className = "day-box";

    const num = document.createElement("div");
    num.className = "day-number";
    num.textContent = day;
    box.appendChild(num);

    if (studyData[dateKey]) {
      studyData[dateKey].forEach(entry => {
        const div = document.createElement("div");
        div.className = "subject-block";
        div.textContent = entry.subject;
        div.style.background = getColorForSubject(entry.subject);
        div.style.height = `${(entry.minutes / maxMinutes) * 100}%`;
        box.appendChild(div);
      });
    }

    calendar.appendChild(box);
  }
}

function getColorForSubject(subject) {
  const colors = {
    23412: "#f4a261",
    24112: "#2a9d8f",
    26020: "#e76f51",
    26120: "#52d18b",
    27112: "#4784b1",
    28112: "#eace10",
  };
  return colors[subject] || "#aaa";
}

createCalendar();
