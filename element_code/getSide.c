	MMA7660_Orientation_t side = MMA7660_GetSide();
	
	if(orient == Front) {
		return "Front";
	} else if(orient == Back) {
		return "Back";
	} else {
		return "Unknown";
	}