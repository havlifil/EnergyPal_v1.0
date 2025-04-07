import { dataStore } from "./datastore.js";
import { pushDataToChart } from "./chart.js";
import utils from "./utils.js"
// fetch temperatures
export function fetchMeasurements(){
    // get measurement chart from datastore
    let chart = dataStore.getChart("measurements");
    // fetch measurements
    fetch("../../api/measurements/getLatestMeasurement.php")
    .then(response => response.json())
    .then(data => {
        if(data.success){
            if(data.data.measurement_unixtime !== dataStore.getVariable("measurementsFetch")){
                let temp1 = (data.data.temp1 == null) ? null : data.data.temp1.toFixed(1);
                let temp2 = (data.data.temp2 == null) ? null : data.data.temp2.toFixed(1);
                let temp3 = (data.data.temp3 == null) ? null : data.data.temp3.toFixed(1);
                let temp4 = (data.data.temp4 == null) ? null : data.data.temp4.toFixed(1);
                let temp5 = (data.data.temp5 == null) ? null : data.data.temp5.toFixed(1);
                let temp6 = (data.data.temp6 == null) ? null : data.data.temp6.toFixed(1);
  
                // update texts
                document.getElementById("temp1").innerText = `${temp1} °C`;
                document.getElementById("temp2").innerText = `${temp2} °C`;
                document.getElementById("temp3").innerText = `${temp3} °C`;
                document.getElementById("temp4").innerText = `${temp4} °C`;
                document.getElementById("temp5").innerText = `${temp5} °C`;
                document.getElementById("temp6").innerText = `${temp6} °C`;
                if(dataStore.getVariable("measurementsFetch") !== 0){
                    // add measurements to chart
                    let datetime = luxon.DateTime.fromFormat(data.data.measurement_datetime, "yyyy-MM-dd HH:mm:ss").toJSDate();
                    pushDataToChart(chart, datetime, data.data.temp1, 1);
                    pushDataToChart(chart, datetime, data.data.temp2, 0);
                    pushDataToChart(chart, datetime, data.data.temp3, 2);
                    pushDataToChart(chart, datetime, data.data.temp4, 4);
                    pushDataToChart(chart, datetime, data.data.temp5, 5);
                    pushDataToChart(chart, datetime, data.data.temp6, 3);
                }
                // asign new value to measurementsFetch
                dataStore.setVariable("measurementsFetch", data.data.measurement_unixtime);
            }
        }
    })
    .catch(error => console.error("Error fetching measurements: ", error));
    // adjust charts min and max
    let max = new Date();
    let min = new Date();
    min.setSeconds(min.getSeconds() - dataStore.getVariable("actualChartRange"));
    chart.options.scales.x.suggestedMin = min;
    chart.options.scales.x.suggestedMax = max
    // remove data that is not in scale
    let threshold = new Date();
    threshold.setSeconds(threshold.getSeconds() - dataStore.getVariable("actualChartRange") - 180);
    chart.data.datasets[0].data = chart.data.datasets[0].data.filter(value => value.x >= threshold);
    chart.data.datasets[1].data = chart.data.datasets[1].data.filter(value => value.x >= threshold);
    chart.data.datasets[2].data = chart.data.datasets[2].data.filter(value => value.x >= threshold);
    chart.data.datasets[3].data = chart.data.datasets[3].data.filter(value => value.x >= threshold);
    chart.data.datasets[4].data = chart.data.datasets[4].data.filter(value => value.x >= threshold);
    chart.data.datasets[4].data = chart.data.datasets[4].data.filter(value => value.x >= threshold);
    chart.update();
}
// fetch states
export function fetchStates(){
    fetch("../../api/states/getLatestStates.php")
    .then(response => response.json())
    .then(data => {
        if(data.success){
            if(data.data.states_unixtime !== dataStore.getVariable("statesFetch")){
                for(let i = 0; i<4; i++){
                    let ID = "OUT_" + (i+1);
                    let element = document.getElementById(ID);
                    let newState = (data.data[ID] === 1) ? utils.colors.stateGreen : utils.colors.stateRed;
                    if(element.style.backgroundColor !== newState){
                        element.style.backgroundColor = (data.data[ID] === 1) ? utils.colors.stateGreen : utils.colors.stateRed;
                    }
                }
                for(let i = 0; i<6; i++){
                    let ID = "IN_" + (i+1);
                    let element = document.getElementById(ID);
                    element.style.backgroundColor = (data.data[ID] === 1) ? utils.colors.stateGreen : utils.colors.stateRed;
                }
            }
            dataStore.setVariable("statesFetch", data.data.states_unixtime);
        }
    })
    .catch(error => console.error("Error fetching temperatures: ", error));
}