/* TODO: Remove test values after library completed */
let testArray: Select.Options.t = [|
  {
    value: "test 1",
    displayText: "test 1 display",
  },
  {
    value: "test 2",
    displayText: "test 2 display",
  }
|];

let handleSelect = (selectedValue) => Js.log(selectedValue);

ReactDOMRe.renderToElementWithId(<Select optionsList={testArray} onSelect={handleSelect} />, "index");
