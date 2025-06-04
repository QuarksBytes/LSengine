use serde::{Serialize, Deserialize};

use crate::componant_parser;

#[derive(Serialize, Deserialize, Debug)]
pub struct DesignPinParsed{
   pub name: String,
   pub id: u32,
}


#[derive(Serialize, Deserialize, Debug)]
pub struct DesignComponantParsed{
   pub identity: String,
   pub name:String,
   pub id:u32,
   pub pins: Vec<DesignPinParsed>,
}


#[derive(Serialize, Deserialize, Debug)]
pub struct ConnectionParsed{
   pub p0: u32,
   pub p1: u32,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct DesignParsed{
    pub name: String,
    pub version: String,
    pub description: String,
    #[serde(default)]
    pub components: Vec<DesignComponantParsed>,
    #[serde(default)]
    pub connections: Vec<ConnectionParsed>,
    #[serde(default)]
    pub dependencies: Vec<componant_parser::ComponantParsed>,
}


pub fn read_design_from_file(file_path: &str) -> Result< DesignParsed, Box<dyn std::error::Error>> {
    let file = std::fs::File::open(file_path)?;
    let reader = std::io::BufReader::new(file);
    let design:DesignParsed = serde_json::from_reader(reader)?;
    Ok(design)
}