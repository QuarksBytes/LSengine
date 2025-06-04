use serde::{Serialize, Deserialize};


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

#[derive(Debug, Serialize, Deserialize)]
pub  struct LogicalParsed{
     pub pins: Pins,
     pub logic:String
}

#[derive(Debug, Serialize, Deserialize)]
pub  struct ElectricalParsed{
     pub pins: Pins,
     pub logic:String
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


pub fn read_componant_from_file(file_path: &str) -> Result<ComponantParsed, Box<dyn std::error::Error>> {
    let file = std::fs::File::open(file_path)?;
    let reader = std::io::BufReader::new(file);
    let componant: ComponantParsed = serde_json::from_reader(reader)?;
    Ok(componant)
}


pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn componant_parssing_test() {
        let result = read_componant_from_file("sample_componant_format.json");
        assert!(result.is_ok());
        let componant = result.unwrap();
        assert_eq!(componant.name, "2-bit-adder");
        assert_eq!(componant.description, "A simple 2-bit adder circuit");
        assert_eq!(componant.width, 200);
        assert_eq!(componant.height, 400);
        assert_eq!(componant.ctype, "INPUT");

        assert_eq!(componant.logic_simulation.pins.left.len(), 5);
        assert_eq!(componant.logic_simulation.pins.right.len(), 3);
        
    
    }
}
