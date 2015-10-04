THRAY
=====

![](./thray.png?raw=true)

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
