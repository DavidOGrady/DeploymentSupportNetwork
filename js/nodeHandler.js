// Global variables
var last_timestamp = null;
var Data;
var nodesParRow = 3;
var amountOfNodesInRow = 0;
var nodeCounter = 0;

// The user will use this function to trigger the polling process
// to get node data
function startPolling() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // Parse Node data into json
      Data = JSON.parse(this.responseText);
      for(var item in Data){
        // For each document that comes in
        // check if a node interface already exists for the node
        if(doesNodeExist(Data[item].Node_ID)){
          // if it does exist. Just append the data to the node interface
          appendNodeData(Data[item]);

        }else{
        // else, Create a node interface for the node.
        buildNode(Data[item]);
        // Increment amountOfNodesInRow so we can keep track of nodes in current row.
        amountOfNodesInRow++;
        IsRowFull(amountOfNodesInRow);
        }
        // Save the Last Timestamp of the last piece of data displayed to the gui
        last_timestamp = Data[item].ts.$date.$numberLong;
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
