	MMA7660_Orientation_t orient = MMA7660_GetOrientation();
	
	if(orient == Left) {
		return "Left";
	} else if(orient == Right) {
		return "Right";
	} else if(orient == Down) {
		return "Down";
	} else if(orient == Up) {
		return "Up";
	} else {
		return "Unknown";
	}
