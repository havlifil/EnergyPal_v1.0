<?php
    require_once('includes/auth.php');
    checkUserLogged();
?>
<!DOCTYPE html>
<html lang="cs">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="assets/css/styles_global.css?v=1.0">
        <link rel="stylesheet" href="assets/css/variables.css?v=1.0">
        <link rel="stylesheet" href="assets/css/styles_navbar.css?v=1.0">
        <link rel="stylesheet" href="assets/css/styles_dashboard.css?v=1.1">
        <script src="https://cdn.jsdelivr.net/npm/chart.js@^3"></script>
        <script src="https://cdn.jsdelivr.net/npm/luxon@^2"></script>
        <script src="https://cdn.jsdelivr.net/npm/chartjs-adapter-luxon@^1"></script>
        <title>EnergyPal</title>
    </head>
    <body>
        <?php include('includes/navbar.html'); ?>
        <div class="container">
            <div id="control">
            <div id="inputs">
                    <div class="in-group" id="IN_1-group">
                        <div class="in-status" id="IN_1"></div>
                        <p>Plynový kotel</p>
                    </div>
                    <div class="in-group" id="IN_2-group">
                        <div class="in-status" id="IN_2"></div>
                        <p>Ohřev TUV</p>
                    </div>
                    <div class="in-group" id="IN_3-group">
                        <div class="in-status" id="IN_3"></div>
                        <p>Oběhové čerpadlo topení</p>
                    </div>
                    <div class="in-group" id="IN_4-group">
                        <div class="in-status" id="IN_4"></div>
                        <p>Vodárna</p>
                    </div>
                    <div class="in-group" id="IN_5-group">
                        <div class="in-status" id="IN_5"></div>
                        <p><span class="unused">Nezapojeno</span></p>
                    </div>
                    <div class="in-group" id="IN_6-group">
                        <div class="in-status" id="IN_6"></div>
                        <p><span class="unused">Nezapojeno</span></p>
                    </div>
                </div>
                <div id="measurements">
                    <div class="measurement">
                        <p class="measurement-name">Plynový boiler</p>
                        <p id="temp2">no-data</p>
                    </div>
                    <div class="measurement">
                        <p class="measurement-name">Elektrický boiler</p>
                        <p id="temp1">no-data</p>
                    </div>
                    <div class="measurement">
                        <p class="measurement-name">Oběhové čerpadlo TUV</p>
                        <p id="temp3">no-data</p>
                    </div>
                    <div class="measurement">
                        <p class="measurement-name">Voda kotel</p>
                        <p id="temp6">no-data</p>
                    </div>
                    <div class="measurement">
                        <p class="measurement-name">Venkovní teplota</p>
                        <p id="temp4">no-data</p>
                    </div>
                    <div class="measurement">
                        <p class="measurement-name">Vnitřní teplota</p>
                        <p id="temp5">no-data</p>
                    </div>
                </div>
                <div id="outputs">
                    <button type="button" class="out-button" id="OUT_1-button">
                        <div class="out-status" id="OUT_1"></div>
                        <p>Oběhové čerpadlo TUV</p>
                    </button>
                    <button type="button" class="out-button" id="OUT_2-button">
                        <div class="out-status" id="OUT_2"></div>
                        <p><span class="unused">Nezapojeno</span></p>
                    </button>
                    <button type="button" class="out-button" id="OUT_3-button">
                        <div class="out-status" id="OUT_3"></div>
                        <p><span class="unused">Nezapojeno</span></p>
                    </button>
                    <button type="button" class="out-button" id="OUT_4-button">
                        <div class="out-status" id="OUT_4"></div>
                        <p><span class="unused">Nezapojeno</span></p>
                    </button>
                </div>
            </div>
            <div id="graph-ranges">
                <button type="button" class="range-button" id="range-quarter-hour">15 minut</button>
                <button type="button" class="range-button" id="range-half-hour">30 minut</button>
                <button type="button" class="range-button" id="range-hour">1 hodina</button>
                <button type="button" class="range-button" id="range-3-hours">3 hodiny</button>
                <button type="button" class="range-button" id="range-12-hours">12 hodin</button>
                <button type="button" class="range-button" id="range-24-hours" autofocus>24 hodin</button>
                <button type="button" class="range-button" id="range-48-hours" autofocus>48 hodin</button>
            </div>
            <div id="charts">
                <canvas id="measurementsChart"></canvas>
            </div>
        </div>
        <script type="module" src="scripts/app_dashboard.js?v=1.1"></script>
    </body>
</html>