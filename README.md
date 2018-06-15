# Reason-React-Select

A nice select box for use within reason react. Feel free to fork, copy/paste, or improve  
the component.

Usage:

Add the component to your project. The base component will accept a list of options  
that have the form `{ value: <value>, displayText: <displayText> }`. It also accepts  
a callback `onSelect`. It has a default value that logs to the console, so pass in a  
function that accepts a single argument for the selectedValue.

Styling:

Styling is done with stylesheets. The wrapping component is namespaced to `o-reason-selected`  
with the sub-components as `__<sub-component>`. Check the source for the full breakdown of  
each part.
