	MMA7660_Orientation_t orient = MMA7660_GetOrientation();
	
	if(orient == MMA7660_Left) {
		return "Left";
	} else if(orient == MMA7660_Right) {
		return "Right";
	} else if(orient == MMA7660_Down) {
		return "Down";
	} else if(orient == MMA7660_Up) {
		return "Up";
	} else {
		return "Unknown";
	}
