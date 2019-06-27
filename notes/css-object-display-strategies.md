# CSS Object Display Strategies
HTML elements on a webpage have their location determined by their positioning in the DOM and certain CSS attributes.  An element will typically fall below the item before it.
~~~
<body>
 <p>It is nice weather in Baltimore this afternoon.</p>
 <p>San Francisco is muggy as ever though.</p>
</body>
~~~

In this example, the second statement about San Francisco falls below the statement about Baltimore.  Any extra space to the right of the first sentence will be unused.

## The "Display" Attribute
Perhaps the most important CSS attribute when determining an element's attribute on the page, "display" may be set to block, inline, none.  Block elements demand a whole line of space.  The <p> tags seen above are block elements and they each take up an entire line of space.  Inline displays, when chained after each other, all appear on the same line.
~~~
<body>
 <span>I once met an old man in Atlanta.</span>
 <span>The best city for experiencing night life is Madrid.</span>
</body>
~~~
These two sentences wrapped in <span> tags will appear on the same line with no separation between them horizontally.  A series of inline elements constitute one line.  Note that a block item following an inline displayed item will take one full line to itself.

## Positioning Strategies
There are four different types of positioning in CSS: static, fixed, relative, and absolute.  The default strategy for determing an item's location is "static".  An HTML object's location in the DOM determines where it will appear on-screen.  Additionally, offsets may move the object on up/down and left/right in the plane.

### Static and Relative
Static elements typically follow the element above them directly below or to the right, in the case where both are inline displays.  These elements cannot be moved by offset specifications.  Offsets are ignored when on a statically positioned HTML element.  Relative positions use the same overarching strategy as static, but allow the element to be further modified by hard-coded offsets in the X and Y axes.  These offsets are specifed with the CSS attributes top, bottom, left, and right.  A relatively positioned element with an offset does not count the offset when determining where the element following it should go.  It is possible to have awkward positioning and overlap this way.

### Fixed and Absolute
The other two enums for positioning, Fixed and Absolute, are not affected by sibling elements at all.  Fixed items appear at the same point on the screen regardless of where you scroll.  Annoying popups that follow you around are fixed elements.  Bars at the top of the page to help with navigation are often fixed. These elements which appear glued to the screen, can be placed anywhere in the DOM, only the offset parameters affect their positioning.  This is unlike absolute items which are located within their containing element.  The offset determines where in the container, the element can be found.  For instance, top:0, left:0 would result in the elements touching top-left corners

### Positioning Summary
- Static uses the display attribute rules and position in the DOM.
- Relative is the same as static but also allows cosmetic offsets which do not affect subsequent item placement
- Fixed elements location in the DOM is irrelevant, they follow scrolling and exist at their offset
- Absolute elements position themselves along the top/bottom and left/right of their parent and shift from there.