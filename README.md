THRAY
=====

![](./thray.gif?raw=true)

Thray is a generalized scraper/consumer thing. More information coming.

Background
----------

```
2015-09-11 14:42:28     WAMPA_STOMPA    i'll crawl through to the point that was actually 
crawling
2015-09-11 14:42:44     WAMPA_STOMPA    there is really nothing interesting about the 
implementation, and the architecture is pretty straight forward
2015-09-11 14:43:01     WAMPA_STOMPA    you just have producers that are crawling and pushing 
into a shared queue for the consumers
2015-09-11 14:43:13     WAMPA_STOMPA    the consumers all have their own db they are writing to
2015-09-11 14:43:21     WAMPA_STOMPA    then at the end the dbs are condensed into a single db

...

2015-09-11 15:51:06     Xamayon the crawler needs a massive queue of links, which are 
provided to workers, workers grab the data at the link and insert it into something, 
analyzers take that data and mark the link in the queue either done or failed, and if 
done, grab more links out of the data if textual, or save the file sanely if binary
2015-09-11 15:51:35     Xamayon if failed, it goes back into queue and gets processed again
2015-09-11 15:52:06     Xamayon that's the general idea atleast, there are a few tricky parts
2015-09-11 15:52:50     Xamayon If I can get this working for DA, I'll probably use it to 
redo pixiv too
```

General Architecture
--------------------

Tech involved:
* C++
* Riak (for distributing scraped information, deduping stuff)
* Mother Postgres for processed data (notes text, usernames, reblogs, whatever)
* Whatever random libraries we need for C++

Scraper
=======

The Scrapers are distributed, small C++ processes that are responsible for pulling endpoints out of a distributed queue. Scrapers will hit the tumblr API for that data, put it into Riak, mark the username as scraped (with a date?) , stick a new job into the "To Be Processed" queue and move onto the next item in the "To Be Scraped" queue. This should also include any media associated, like images. MP3/videos too, maybe?

Processor
=========

Processors pulled scraped blobs out of Riak and turn them into identified data which goes into Postgres. This includes things like the username, note text, tags, date posted, etc. Processors continually pull blobs from Riak for transformations that will be loaded into Postgres. We should be able to re-populate postgres anytime with data from Riak.
