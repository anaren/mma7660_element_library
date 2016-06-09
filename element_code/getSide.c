	MMA7660_Orientation_t side = MMA7660_GetSide();
	
	if(orient == MMA7660_Front) {
		return "Front";
	} else if(orient == MMA7660_Back) {
		return "Back";
	} else {
		return "Unknown";
	}
