use crate::city::{City};

pub struct App {
	city: Option<City>,

	tick: usize,
}

impl App {
	pub fn new() -> Self {
		Self {
			city: Option::None,
			tick: 0,
		}
	}
}