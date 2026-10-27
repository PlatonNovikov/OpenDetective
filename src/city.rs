//boykisser
//writing it a year later. I have no idea why i wrote "boykisser", but im leaving it here lol
//writing this comment one more year later and i'm taking it to Rust. This is a legacy code now

use crate::npc::{Npc};

pub struct City {
	pub name: String,

	map: Vec<Vec<BuildingId>>,

	npcs: Vec<Npc>,
	buildings: Vec<Building>,
	floors: Vec<Floor>,
}

impl City {
	fn gen_map(width: usize,  height: usize) -> Vec<Vec<Building>> {

	}

	pub fn new(name: String, width: usize, height: usize) -> Self {
		let city = Self {
			name,
			map: Vec::new(),
			npcs: Vec::new(),
		};

		city
	}
}

enum FloorType {
	Residential(ResidentialFloor),
	Office(OfficeFloor)
}

struct ResidentialFloor {
	
}

struct OfficeFloor {

}

struct Floor {
	floor_number: usize,
	floor_type: FloorType,
	parent_building: BuildingId,
	current_npcs: Vec<NpcId>,
}


pub struct Building {
	name: String,
	pos: Position,
}

pub struct Position {
	pub x: usize,
	pub y: usize,
}

pub enum Location {
	Outside(Position),
	Floor(FloorId),
}

type FloorId = usize;
type BuildingId = usize;
type NpcId = usize;