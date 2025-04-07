import { dataStore } from "./datastore.js";
import utils from "./utils.js";
// create new line chart
export function createMeasurementsChart(canvasID, datasets, nameChart, nameX, nameY, yMin, yMax){
    const ctx = document.getElementById(canvasID);
    const config = {
        type: 'line',
        data: { datasets: datasets },
        options: {
            animation: false,
            plugins: {
                title: { 
                    display: true, 
                    text: nameChart, 
                    color: utils.colors.textColor,
                    font:{
                        family: "Oxanium",
                        size: 16,
                        weight: 400
                    } 
                },
                legend: { 
                    labels: { 
                        color: utils.colors.textColor,
                        font: {
                            family: "Oxanium",
                            size: 14
                        },
                        usePointStyle: true,
                        generateLabels: function(chart) {
                            const labels = Chart.defaults.plugins.legend.labels.generateLabels(chart);
                            labels.forEach(label => {
                                const dataset = chart.data.datasets[label.datasetIndex];
                                if (dataset) {
                                    label.fillStyle = dataset.borderColor;
                                    label.pointStyle = "rectRounded";
                                }
                            });
                            return labels;
                        }
                    },
                    position: "bottom"
                }
            },
            scales: {
                x: {
                    type: 'time',
                    time: { unit: 'hour', tooltipFormat: 'yyyy-MM-dd HH:mm', stepsize: 1 },
                    ticks: {
                        source: 'auto',
                        autoSkip: false,
                        callback: function(value, index, values) {
                            let datetime = luxon.DateTime.fromMillis(values[index].value)
                            .setZone('Europe/Berlin')
                            .toFormat('yyyy-MM-dd HH:mm');
                            return datetime;
                        },
                        color: utils.colors.textColor,
                        font:{
                            family: "Oxanium",
                            size: 12
                        }
                    },
                    title: { 
                        display: true, 
                        text: nameX, 
                        color: utils.colors.textColor,
                        font:{
                            family: "Oxanium",
                            size: 14
                        }
                     },
                    grid: { color: utils.colors.primaryColor }
                },
                y: {
                    suggestedMin: yMin,
                    suggestedMax: yMax,
                    title: { 
                        display: true, 
                        text: nameY, 
                        color: utils.colors.textColor,
                        font:{
                            family: "Oxanium",
                            size: 14
                        }
                     },
                    ticks: { 
                        color: utils.colors.textColor,
                        font:{
                            family: "Oxanium",
                            size: 12
                        } 
                    },
                    grid: { color: utils.colors.primaryColor }
                }
            },
            elements:{
                point:{
                    radius: 0
                }
            },
            responsive: true,
            maintainAspectRatio: false
        }
    }
    let chart = new Chart(ctx, config);
    Chart.defaults.font.family = "Oxanium";
    chart.update();
    return chart;
}
// push new data to chart
export function pushDataToChart(chart, xValue, yValue, datasetIndex){
    chart.data.datasets[datasetIndex].data.push({x: xValue, y: yValue});
}
// earase chart and fill it with new data in set range
export function fillMeasurementsChart(rangeSeconds){
    // asign actualChartRange the value of new range
    dataStore.setVariable("actualChartRange", rangeSeconds);
    // earase chart
    const chart = dataStore.getChart("measurements");
    chart.data.datasets[0].data = [];
    chart.data.datasets[1].data = [];
    chart.data.datasets[2].data = [];
    chart.data.datasets[3].data = [];
    chart.data.datasets[4].data = [];
    chart.data.datasets[5].data = [];
    // adjust charts min and max
    let max = new Date();
    let min = new Date();
    min.setSeconds(min.getSeconds() - dataStore.getVariable("actualChartRange"));
    chart.options.scales.x.suggestedMin = min;
    chart.options.scales.x.suggestedMax = max
    // fetch data
    let rangeFrom = new Date();
    rangeFrom.setSeconds(rangeFrom.getSeconds() - rangeSeconds - 180);
    let rangeTo = new Date();
    let rangeFromSeconds = Math.floor((rangeFrom.getTime() - rangeFrom.getTimezoneOffset() * 60000) / 1000);
    let rangeToSeconds = Math.floor((rangeTo.getTime() - rangeTo.getTimezoneOffset() * 60000) / 1000);
    fetch(`../../api/measurements/getRangeMeasurements.php?from=${rangeFromSeconds}&to=${rangeToSeconds}`)
    .then(response => response.json())
    .then(data => {
        if(data.success){
            data.data.forEach(element => {
                let datetime = luxon.DateTime.fromFormat(element.measurement_datetime, "yyyy-MM-dd HH:mm:ss").toJSDate();
                pushDataToChart(chart, datetime, element.temp1, 1);
                pushDataToChart(chart, datetime, element.temp2, 0);
                pushDataToChart(chart, datetime, element.temp3, 2);
                pushDataToChart(chart, datetime, element.temp4, 4);
                pushDataToChart(chart, datetime, element.temp5, 5);
                pushDataToChart(chart, datetime, element.temp6, 3);
            });
        }
    })
    .catch(error => console.error("Error creating graph: ", error));
    chart.update();
}