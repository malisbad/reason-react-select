# Reason-Select

A nice select box for use within reason react. Feel free to fork, copy/paste, or improve  
the component.

Installation:

`npm install reason-select`

Add `reason-select` to your `bs-dependencies`.

```
{
  ...
  "bs-dependencies": ["reason-select"]
}
```

Usage:

Use the `<ReasonSelect />` component in your project!

`<ReasonSelect />` takes two props: an `optionsList` array of and an `onSelect`  
function.

`optionsList` is an array of `Select.Options.t` that have the form  
`{ value: <value>, displayText: <displayText> }`.

`onSelect` should be a function that accepts one argument, a `selectedValue`. It  
is optional, but only in the sense that it logs the selection to console if it  
doesn't get passed something else to do.

Styling:

The wrapping component is namespaced to `o-reason-select` with the sub-components  
as `__<sub-component>`. Check the source for the full breakdown of each part.

You should add a minimum height and width to `o-reason-select__display`, and probably  
a background colour. Without it, there won't be anything to click on. Default  
styles aren't included (yet), so currently there is maximum freedom to style
as you will.
