#TimelineJS Block

This module creates blocks using the TimelineJS javascript library.

##Installation
To install:

1. Enable TimelineJS Content Types.
2. Enable TimelineJS Block.
3. Download TimelineJS library from https://github.com/VeriteCo/TimelineJS and save it to /sites/all/libraries/ so that timeline.js can be found at /sites/all/libraries/TimelineJS/compiled/js/. I recomend using git clone https://github.com/VeriteCo/TimelineJS.git so you can carry out step 4 easily.
4. Go to /sites/all/libraries/TimelineJS and run git reset --hard a80a7f75e71f018ab3e363543ed547e28034e03a as there are bugs in the current version of the library.
5. Check Status report to ensure that the library is successfully installed.

##Use
1. (Optional) Create Timeline Categories as requierd from the Taxonomy menu -> /admin/structure/taxonomy/timeline_category
2. Create TimelineJS Dates node. -> /node/add/timelinejs-dates. As a minimum:
    1. Fill Headline
    *  Set a start date

3. Setup the number of timeline block you wish to have on your site -> /admin/config/content/timelinejs_config
    1. Set the number of blocks (default is 2)
4. Enable a block.
    1. Go to /admin/structure/block
    *  Select configure next to one of the blocks you have created in step 3. The will show up as Display Timeline 1 through X
    *  Under the "Select Dates for Timeline" fieldset select the TimelineJS Dates you created that you want to display on this block.
    *  Under the "Title Slider Configuration" fieldset enter the name for the timeline. This will display on the title slide of your block's timeline.
    *  Fill in all other options you may want to.
    *  Assign your block to a region and git it a context if needed.
    *  Save your block.
5. View your results.

##Notes
Currently the TimelineJS Chart Content Type exists, is processed by the json and if correct as per the examples given in github. However, they are not currelty generating a plot.
