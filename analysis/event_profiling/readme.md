## Profiling analysis

We have here i) a binary and some generated timing data with the "old" event model where:
- Raisers of events "new" them on the heap.
- The data is contained within a "variant" type for proto messages.
- Event listeners are indexed by their "interested in" type and looked up and called only when needed.
- binary was build as a Release config from commit 66c00943f853588cfad537d6128adb8ad06b805e 
- 1000 loops, one every 5 millis.

... ii) an alternative binary and data for comparison (pending)

...and iii) some analysis thereof =P (pending)
