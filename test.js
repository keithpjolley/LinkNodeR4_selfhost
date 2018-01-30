const mysql   = require('mysql');
const path    = require('path');
const dbconf  = require(path.join('/Users/kjolley/Dropbox/prj/site/node/linknode', 'private', 'mysql', 'dbconf'));
const ls_rw   = dbconf.local.linksprite_rw;
const mydevid  = '00800001eb';
const myapikey = '__devicekey__'
const args     = [mydevid,myapikey];
const query    = 'SELECT devicekey, "foo" AS bar  FROM apikeys WHERE deviceid = ? AND userkey = ?';

var res = "unused";
var connection = mysql.createConnection(ls_rw);
var x = connection.query(query, args, function(error, results) {
  if(error){
    console.log("ERROR: " + JSON.stringify(error));
    res = "fail";
  } else {
    console.log("RESULTS: BEGIN:");
    console.log(JSON.stringify(results));
    res = "waddled";
    res = results;
    console.log("RESULTS: END:");
  }
});
connection.destroy();
console.log("RESULTS: res: " + JSON.stringify(res)); 
