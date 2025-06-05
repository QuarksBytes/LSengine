
pub use  syngine_parser;


fn openDesign(path:&str){
    let mut file = std::fs::File::open(path)
        .expect("Unable to open file");
    
   let componant =  syngine_parser::componant_parser::read_componant_from_file(file_path);
    // 8240231673

}

#[cfg(test)]
mod tests {
   
    #[test]
    fn it_works() {
        
    }
}
