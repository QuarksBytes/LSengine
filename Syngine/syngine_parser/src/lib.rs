

pub mod componant_parser;
pub mod design_parser;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn componant_parsing_test() {
        let result = componant_parser::read_componant_from_file("sample_componant_format.json");
        assert!(result.is_ok());
        let componant = result.unwrap();
      
        println!("{}", componant);
    }

    // #[test]
    // fn design_parsing_test() {
    //     let result = design_parser::read_design_from_file("sample_design_format.json");
    //     assert!(result.is_ok());
    //     let design = result.unwrap();
    //     assert_eq!(design.name, "Sample Design");
    //     assert_eq!(design.version, "1.0");
    //     assert_eq!(design.components.len(), 4);
    //     assert_eq!(design.connections.len(), 3);
    //     assert_eq!(design.dependencies.len(), 2);
    
    // }
}
