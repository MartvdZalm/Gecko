<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Gecko</title>
        <link type="text/css" href="{{ asset('style.css') }}" rel="stylesheet"/>
        <style>

        </style>
    </head>
    <body class="antialiased">

        <div class="calendar">
            <div class="calendar-header">
                <button id="prevMonth">«</button>
                <h2 id="monthAndYear"></h2>
                <button id="nextMonth">»</button>
            </div>
            <table class="calendar-table">
                <thead>
                    <tr>
                        <th>Sun</th>
                        <th>Mon</th>
                        <th>Tue</th>
                        <th>Wed</th>
                        <th>Thu</th>
                        <th>Fri</th>
                        <th>Sat</th>
                    </tr>
                </thead>
                <tbody id="calendar-body">
                    <!-- Calendar dates will be injected here by JavaScript -->
                </tbody>
            </table>
        </div>
        
        <script type="text/javascript" src="{{ asset('js/app.js') }}"></script>
    </body>
</html>