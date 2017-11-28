var last_timestamp = null;
var Data;
function loadData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      AppendData(this.responseText);
    }
  };
  if(last_timestamp == null){
    // This should only run the first time as last_timestamp will become defined after this
    xhttp.open("GET", "php/httplongpolling.php", true);
    xhttp.send();
  }else{
    // This should run everytime once we get the timestamp data. This timestamp is used
    // by Display.php to fetch only new data as it comes into the db
    xhttp.open("GET", "php/httplongpolling.php?last_timestamp="+last_timestamp, true);
    xhttp.send();
  }

}
function AppendData(xhttp){
  Data = JSON.parse(xhttp);
  for(var item in Data){
    var para = document.createElement("TEXTAREA");
    var t = document.createTextNode(Data[item].data);
    para.appendChild(t);
    document.getElementById("target").appendChild(para);
    // Save the Last Timestamp of the last piece of data displayed to the gui
    last_timestamp = Data[item].ts.$date.$numberLong;
  }
}
