# PROJECT PLAN
*Johan Book*, *Edvin Jakobsson*, *Sara Gabrielli*
MNXB01 2017-10-27

## Ideas
- Compare average temperature between places (using overlay with semi-transparent graphs)
- Prove global warming in Uppsala
  -Calculate difference in temperature for each place over the years (data from Uppsala)
- Look into how it affects the location of the hottest and the coldest day in a year
  
#### Edvin
Look into global warming - Create one or several histograms over the average temperature over the different years in the Uppsala data.

#### Sara 	
Look into how the hottest and coldest day switches over time and look for patterns. Create a histogram over the hottest/coldest day over the different years. Compare with gobal warming.

#### Johan
Compare the average temperature changes in different areas (data sets). Create a histogram over average temperature for several areas over the different years, or the different days. Create cool image

## Project Structure
- code/ - code files
- data/ - data files
- info/ - information about project
- report/ - files for the report
- results/ - produced figures
  
## Objects in code/
- generate_images.C - generates images (Johan Book)
- global_warming.C - stuff (Edvin Jakobsson)
- root_template.C - basic template for using treader and tpoint
- rootlogon.C - script run when root is started
- treader - object to reads data line by line and convert it into tpoints (Johan Book) 
- tpoint - object that stores one point in time-temperature space (Johan Book)
- Sara_Analyze.C - analyzes data (Sara Gabrielli)
- Sara_Producefiles.cpp - reads data from Uppsala and finds highest and lowest temperaturs and corresponding days (Sara Gabrielli)
