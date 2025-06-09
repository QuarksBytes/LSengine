use serde::{Serialize, Deserialize};
use std::fmt::{self, write};
use colored::*;


#[derive(Debug, Serialize, Deserialize)]
pub struct PinParsed {
    pub name: String,
}


#[derive(Debug, Serialize, Deserialize)]
pub struct Pins {
     #[serde(default)]
    pub left: Vec<PinParsed>,
     #[serde(default)]
    pub right: Vec<PinParsed>,
     #[serde(default)]
    pub top: Vec<PinParsed>,
     #[serde(default)]
    pub bottom: Vec<PinParsed>,
}

impl fmt::Display for Pins {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        //printing top pins
        if !self.top.is_empty(){
          self.top.iter().for_each(|pin| {
            write!(f, "{} ", pin.name.green()).unwrap();
           });
       }
       else {
           write!(f,"-----").unwrap()
       }

        write!(f,"\n").unwrap();

        //printing left pins

        if !self.left.is_empty(){
            self.left.iter().for_each(|pin| {
                write!(f, "{} \n", pin.name.green()).unwrap();
            });
        }
        

       //printing bottom  pins
       if !self.bottom.is_empty(){
          write!(f,"   ").unwrap(); 
          self.bottom.iter().for_each(|pin| {
             write!(f, "{} ", pin.name.green()).unwrap();
          });
      }
       else {
         write!(f,"   -----").unwrap()
      }

        write!(f,"\n")
    }
    
}



#[derive(Debug, Serialize, Deserialize)]
pub  struct LogicalParsed{
     pub pins: Pins,
     pub logic:String
}

impl fmt::Display for LogicalParsed {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f,
    "{}
     Logic 
     {}
    ",
     self.pins,
     self.logic
        )
    }
}




#[derive(Debug, Serialize, Deserialize)]
pub  struct ElectricalParsed{
     pub pins: Pins,
     pub logic:String
}

impl fmt::Display for ElectricalParsed {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f,
    "{}
     Logic
     {}
    ",
     self.pins,
     self.logic
        )
    }
}






#[derive(Debug, Serialize, Deserialize)]
pub struct ComponantParsed{
    pub name: String,
    pub description: String,
    pub width: u64,
    pub height: u64,
     #[serde(rename = "type")]
    pub ctype: String,
     #[serde(rename = "Logic_simulation")]
    pub logic_simulation: LogicalParsed,
     #[serde(rename = "Electrical_simulation")]
    pub electrical_simulation: ElectricalParsed,
}


impl fmt::Display for ComponantParsed {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    
write!(f,
" {}
            
   Name: {}
   Description: {}
   Width: {}
   Height: {}
   Type: {}

   {}
   {}

   {}
   {}
            ",
            "Componant Description".truecolor(52, 235, 201),
            self.name.green(),
            self.description.blue(),
            self.width.to_string().yellow(),
            self.height.to_string().yellow(),
            self.ctype.cyan(),
            "Logic Simulation".truecolor(52, 235, 201),
            self.logic_simulation,
            "Electrical Simulation".truecolor(52, 235, 201),
            self.electrical_simulation
        )
    }
}


pub fn read_componant_from_file(file_path: &str) -> Result<ComponantParsed, Box<dyn std::error::Error>> {
    let file = std::fs::File::open(file_path)?;
    let reader = std::io::BufReader::new(file);
    let componant: ComponantParsed = serde_json::from_reader(reader)?;
    Ok(componant)
}