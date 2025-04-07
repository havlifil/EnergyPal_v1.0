import { dataStore } from "./datastore.js";
import { sendCommand } from "./connection.js";
import utils from "./utils.js";
// send command to change the output state
export function changeOutState(out){
    if(dataStore.getVariable("deviceConnected")){
        const ID = "OUT_" + out;
        fetch("../../api/states/getLatestStates.php")
        .then(response => response.json())
        .then(data => {
            if(data.success){
                if(data.data[ID] === 1){
                    var confirmed = confirm("Opravdu chcete vypnout OUT_" + out + "?");
                    if(confirmed){
                        sendCommand("outoff", out);
                        document.getElementById(ID).style.backgroundColor = utils.colors.stateOrange;
                    }
                } else {
                    var confirmed = confirm("Opravdu chcete zapnout OUT_" + out + "?");
                    if(confirmed){
                        sendCommand("outon", out);
                        document.getElementById(ID).style.backgroundColor = utils.colors.stateOrange;
                    }
                }
            }
        })
        .catch(error => console.error("Error fetching states: ", error));
    }
}