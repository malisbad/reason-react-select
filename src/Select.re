/* This is the basic component. */
let component = ReasonReact.statelessComponent("Select");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className=".c-reason-select">
      <SelectInput />
      <OptionsList />
    </div>
};
