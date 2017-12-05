// Global variables
var last_timestamp = null;
var Data;
var nodesParRow = 3;
var amountOfNodesInRow = 0;
var nodeCounter = 0;
var pollingSwitch = false;
var pollingIntervalObject;
var switchbutton;

// This function will be used as a switch to turn on and off the polling process
function pollSwitch() {
    pollingSwitch = !pollingSwitch;
    if (pollingSwitch){
      // Start polling and change button to off switch
      pollingIntervalObject = setInterval(function(){ pollData() }, 1000);
      // change button
      switchbutton = document.getElementById("switch");
      switchbutton.className = "btn btn-danger";
      switchbutton.innerHTML = "Stop Polling";
    }else{
      // Stop polling interval.
      clearInterval(pollingIntervalObject);
      // Change button
      switchbutton = document.getElementById("switch");
      switchbutton.className = "btn btn-primary";
      switchbutton.innerHTML = "Start Polling";
    }

}


// The user will use this function to trigger the polling process
// to get node data
async function pollData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = async function() {
    if (this.readyState == 4 && this.status == 200) {
      // Parse Node data into json
      Data = JSON.parse(this.responseText);
      for(var item in Data){
        // For each document that comes in
        // check if a node interface already exists for the node
        if(doesNodeExist(Data[item].Node_ID)){
          // if it does exist. Just append the data to the node interface
          await appendNodeData(Data[item]);

        }else{
        // else, Create a node interface for the node.
        await buildNode(Data[item]);
        // Increment amountOfNodesInRow so we can keep track of nodes in current row.
        amountOfNodesInRow++;
        await IsRowFull(amountOfNodesInRow);
        }
      }
      // Save most recent last_timestamp
      if(await getMostRecentTimestamp(Data)){
        last_timestamp = await getMostRecentTimestamp(Data);
      }
    }
  };
  if(last_timestamp == null){
    // This should only run the first time as last_timestamp will become defined after this
    xhttp.open("GET", "php/Display.php", true);
    xhttp.send();
  }else{
    // This should run everytime once we get the timestamp data. This timestamp is used
    // by Display.php to fetch only new data as it comes into the db
    xhttp.open("GET", "php/Display.php?last_timestamp="+last_timestamp, true);
    xhttp.send();
  }
};

// This function should be used to append some data to some node div
function appendNodeData(NodeInfo) {
  // We have to target the textarea in each node and append data to it
  // NodeInfo.Node_ID = Node's ID
  // NodeInfo.data = Nodes data to be appended.
  var target = document.getElementById("Textarea " + NodeInfo.Node_ID);
  var newData = document.createTextNode(NodeInfo.data);
  target.appendChild(newData);

};

// This function should be used to build a platform/box/tablecell for a Node
// ands its data.
function buildNode(item) {
  // create div for node
  var col = document.createElement("div");
  col.className = 'col';
  col.id = 'NodeID ' + item.Node_ID;

  // Append a header with the Nodes name to the div
  var header = document.createElement("h4");
  col.appendChild(header);
  var h = document.createTextNode("Node "+item.Node_ID);
  header.appendChild(h);

  // create textarea for nodeData
  var textarea = document.createElement("textarea");
  textarea.id = 'Textarea ' + item.Node_ID;
  col.appendChild(textarea);
  var t = document.createTextNode(item.data);
  textarea.appendChild(t);

  // Append to GUI
  document.getElementById("target").appendChild(col);
  // Might be useful to count all the nodes in use
  nodeCounter++;
};

// Helper Functions

function IsRowFull(currentAmount){
  if(currentAmount == nodesParRow){
    var w100tag = document.createElement("div");
    w100tag.className = 'w-100';
    document.getElementById("target").appendChild(w100tag);
    amountOfNodesInRow = 0;
  }
};


// Should return true if a node interface exists for the give Node_ID
function doesNodeExist(Node_ID) {
    var posNode = document.getElementById('NodeID ' + Node_ID);
    if(posNode){
      return true;
    }else{
      return false;
    }
}
// Find the most recent timestamp from the dataset
async function getMostRecentTimestamp(dataset){
  // Save the Last Timestamp of the last piece of data displayed to the gui
  var mostRecentTime;
  if(dataset){
    try{
    mostRecentTime = dataset[0].ts.$date.$numberLong;
  }catch(e){ // Catch error throwing for when dataset is undefined 
  }
    for(var item in dataset){
      if(mostRecentTime < dataset[item].ts.$date.$numberLong){
        mostRecentTime = dataset[item].ts.$date.$numberLong;
      }
    }
    return mostRecentTime;
  }else{
    // return null and keep the most recent before this function
    return null;
  }
}
