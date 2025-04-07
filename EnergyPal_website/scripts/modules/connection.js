import { dataStore } from "./datastore.js";
import utils from "./utils.js"
// send command to EnergyPal
export function sendCommand(operation, value){
    const socket = dataStore.getWebSocket();
    if(socket.readyState === WebSocket.OPEN){
        const data = {
            action: "sendmessage",
            deviceID: dataStore.getVariable("deviceID"),
            operation: operation,
            value: value
        }
        socket.send(JSON.stringify(data));
        console.log("Sent command: ", JSON.stringify(data));
    }
}
// execute valid WebSocket message
export function executeMessage(operation, value){
    switch(operation){
        case "pong":
            if(value === dataStore.getVariable("lastPing")){
                dataStore.setVariable("lastPong", Math.floor((Date.now()/1000)+3600));
            }
            break;
    }
}
// check if pong from EnergyPal was received
export function checkDeviceConnection(){
    const unixTimeNow = Math.floor((Date.now()/1000)+3600);
    if((unixTimeNow - dataStore.getVariable("lastPing")) >= 3){
        if((dataStore.getVariable("lastPong") - dataStore.getVariable("lastPing")) >= 0){
            dataStore.setVariable("deviceConnected", true);
        } else {
            dataStore.setVariable("deviceConnected", false);
        }
    }
    let color = (dataStore.getVariable("deviceConnected")) ? utils.colors.stateGreen : utils.colors.stateRed;
    document.getElementById("EnergyPal-status").style.backgroundColor = color;
}
// ping EnergyPal
export function pingEnergyPal(){
    const socket = dataStore.getWebSocket();
    if(socket.readyState === WebSocket.OPEN){
        const unixTimeNow = Math.floor((Date.now()/1000)+3600);
        const data = {
            action: "sendmessage",
            deviceID: dataStore.getVariable("deviceID"),
            operation: "ping",
            value: unixTimeNow
        }
        socket.send(JSON.stringify(data));
        dataStore.setVariable("lastPing", unixTimeNow);
    }
}