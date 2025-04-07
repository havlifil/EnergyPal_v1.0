require('dotenv').config();

const DEVICE_ID = process.env.user_DEVICE_ID;

const DEFAULT_CHART_RANGE = 24*3600;
const MEASUREMENTS_DATASETS = [
    {
        tension: 0,
        label: 'Plynový boiler',
        data: [],
        borderColor: utils.colors.graphGreen,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }, {
        tension: 0,
        label: 'Elektrický boiler',
        data: [],
        borderColor: utils.colors.graphBlue,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }, {
        tension: 0,
        label: 'Oběhové čerpadlo TUV',
        data: [],
        borderColor: utils.colors.graphOrange,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }, {
        tension: 0,
        label: 'Voda kotel',
        data: [],
        borderColor: utils.colors.graphDarkBlue,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }, {
        tension: 0,
        label: 'Venkovní teplota',
        data: [],
        borderColor: utils.colors.graphViolet,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }, {
        tension: 0,
        label: 'Vnitřní teplota',
        data: [],
        borderColor: utils.colors.graphYellow,
        fill: false,
        spanGaps: true,
        clip: { left: 0, right: false, top: false, bottom: false },
        parsing: false
    }
];
const STATES_DATASETS = [
    {
        label: 'OUTPUT 1',
        borderColor: 'red',
        stepped: true,
        spanGaps: true,
        clip: { left: 0, right: true, top: false, bottom: false },
        parsing: false
    }
];

import { dataStore } from "./modules/datastore.js";
import { changeOutState } from "./modules/control.js";
import { fetchMeasurements, fetchStates } from "./modules/fetch.js";
import { pingEnergyPal, checkDeviceConnection, executeMessage } from "./modules/connection.js";
import { createMeasurementsChart, fillMeasurementsChart } from "./modules/chart.js";
import utils from "./modules/utils.js";


function main(){
    // set variables
    dataStore.setVariable("lastPing", 1);
    dataStore.setVariable("lastPong", 0);
    dataStore.setVariable("measurementsFetch", 0);
    dataStore.setVariable("statesFetch", 0);
    dataStore.setVariable("deviceConnected", false);
    dataStore.setVariable("deviceID", DEVICE_ID);

    // establish WebSocket connection
    const ws = new WebSocket(process.env.user_API_URL)
    // set WebSocket events
    ws.onopen = function(event){
        console.log("[WebSocket] Connection established.");
        dataStore.setWebSocket(ws);
        pingEnergyPal();
    };
    ws.onmessage = function(event){
        console.log(`[WebSocket] Message received: ${event.data}`);
        const data = JSON.parse(event.data);
        if(('deviceID' in data) && ('operation' in data) && ('value' in data)){
            if(data.deviceID === DEVICE_ID){
                executeMessage(data.operation, data.value);
            } else {
                console.log("[WebSocket] DeviceID doesn't match.")
            }
        } else {
            console.log("[WebSocket] Received invalid message.");    
        }
    };
    ws.onclose = function(event){
        if(event.wasClean){
            console.log(`[WebSocket] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
        } else {
            console.log("[WebSocket] Connection died.");
        }
    };
    ws.onerror = function(error){
        console.error("[WebSocket] Error occured:", error);
    };

    // create new line chart for measurements
    const measurementsChart = createMeasurementsChart("measurementsChart", MEASUREMENTS_DATASETS, "GRAF TEPLOT", "čas", "teplota [°C]", 0, 50);
    dataStore.setChart("measurements", measurementsChart);
    // set actual chart range to DEFAULT
    dataStore.setVariable("actualChartRange", DEFAULT_CHART_RANGE);
    // fill the chart with values in default range
    fillMeasurementsChart(DEFAULT_CHART_RANGE);

    document.getElementById("OUT_1-button").addEventListener("click", () => changeOutState(1));
    document.getElementById("OUT_2-button").addEventListener("click", () => changeOutState(2));
    document.getElementById("OUT_3-button").addEventListener("click", () => changeOutState(3));
    document.getElementById("OUT_4-button").addEventListener("click", () => changeOutState(4));

    document.getElementById("range-quarter-hour").addEventListener("click", () => fillMeasurementsChart(0.25*3600));
    document.getElementById("range-half-hour").addEventListener("click", () => fillMeasurementsChart(0.5*3600));
    document.getElementById("range-hour").addEventListener("click", () => fillMeasurementsChart(3600));
    document.getElementById("range-3-hours").addEventListener("click", () => fillMeasurementsChart(3*3600));
    document.getElementById("range-12-hours").addEventListener("click", () => fillMeasurementsChart(12*3600));
    document.getElementById("range-24-hours").addEventListener("click", () => fillMeasurementsChart(24*3600));
    document.getElementById("range-48-hours").addEventListener("click", () => fillMeasurementsChart(48*3600));

    setInterval(fetchMeasurements, 5000); // fetch temperatures every 5 seconds
    setInterval(fetchStates, 1000); // fetch states every 1 second
    setInterval(pingEnergyPal, 30000); // send ping to EnergyPal every 30 seconds
    setInterval(checkDeviceConnection, 1000); // check device connection every 1 second
}

main();