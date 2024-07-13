document.addEventListener("DOMContentLoaded", function() 
{
    const currentDate = new Date();
    let currentMonth = currentDate.getMonth();
    let currentYear = currentDate.getFullYear();

    const monthAndYear = document.getElementById("monthAndYear");
    const calendarBody = document.getElementById("calendar-body");

    function renderCalendar(month, year)
    {
        const firstDay = (new Date(year, month)).getDay();
        const daysInMonth = 32 - new Date(year, month, 32).getDate();

        calendarBody.innerHTML = "";

        const monthName = new Date(year, month).toLocaleString('default', { month: 'long' });
        monthAndYear.textContent = `${monthName} ${year}`;

        let date = 1;
        for (let i = 0; i < 6; i++) {
            const row = document.createElement("tr");

            for (let j = 0; j < 7; j++) {
                const cell = document.createElement("td");
                if (i === 0 && j < firstDay) {
                    const cellText = document.createTextNode("");
                    cell.appendChild(cellText);
                } else if (date > daysInMonth) {
                    break;
                } else {
                    const cellText = document.createTextNode(date);
                    cell.appendChild(cellText);
                    if (date === currentDate.getDate() && year === currentDate.getFullYear() && month === currentDate.getMonth()) {
                        cell.classList.add("current-date");
                    }
                    date++;
                }
                row.appendChild(cell);
            }

            calendarBody.appendChild(row);
        }
    }

    document.getElementById("prevMonth").addEventListener("click", function() {
        currentYear = (currentMonth === 0) ? currentYear - 1 : currentYear;
        currentMonth = (currentMonth === 0) ? 11 : currentMonth - 1;
        renderCalendar(currentMonth, currentYear);
    });

    document.getElementById("nextMonth").addEventListener("click", function() {
        currentYear = (currentMonth === 11) ? currentYear + 1 : currentYear;
        currentMonth = (currentMonth === 11) ? 0 : currentMonth + 1;
        renderCalendar(currentMonth, currentYear);
    });

    renderCalendar(currentMonth, currentYear);
});
