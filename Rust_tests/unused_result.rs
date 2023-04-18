
fn returns_int() -> i32 {
    return 42;
}

fn returns_result_int_int() -> Result<i32, i32> {
    return Ok(42);
}

fn main() {
    returns_int();
    returns_result_int_int();
}
