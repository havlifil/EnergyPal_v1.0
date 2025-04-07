class DataStore {
    constructor(){
        this.variables = {};
        this.charts = {};
        this.webSocket = null;
    }
    setVariable(key, data){
        this.variables[key] = data;
    }
    getVariable(key){
        return this.variables[key];
    }
    setChart(key, chart){
        this.charts[key] = chart;
    }
    getChart(key){
        return this.charts[key];
    }
    setWebSocket(ws){
        this.webSocket = ws;
    }
    getWebSocket(){
        return this.webSocket;
    }
}
export const dataStore = new DataStore;