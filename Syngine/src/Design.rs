
use crate::Component;

struct Design{
    pub name: String,
    pub description: String,
    pub version: String,
    pub author: String,
    pub date_created: String,
    pub date_modified: String,
    pub components: Vec<String>, // FIX ME : change it to ComponentReference from  String
    pub connections: Vec<(String, String)>, // FIX ME : change it to Connection from  vec of String
    pub dependencies: Vec<Component>, // FIX ME : change it to Component from  String
}