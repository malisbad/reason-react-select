let component = ReasonReact.statelessComponent("OptionsList");

let make = _children => {
    ...component,
    render: (_self) => {
        <div className=".c-reason-select__option-list">
        </div>
    }
}